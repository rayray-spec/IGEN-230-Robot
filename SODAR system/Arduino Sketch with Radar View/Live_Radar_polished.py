import re, time, math
import numpy as np
import serial
import matplotlib.pyplot as plt
from matplotlib.colors import to_rgba

PORT, BAUD = 'COM5', 9600
MAX_CM  = 100     # radar range
FADE_S  = 3.0     # seconds before a blip disappears
TRAIL   = math.radians(15)
CYAN, BG, GRID = '#22d3ee', '#0a0f14', '#164e63'

ser = serial.Serial(PORT, BAUD, timeout=1)

fig = plt.figure(figsize=(9, 5.5), facecolor=BG)
ax = fig.add_subplot(projection='polar', facecolor=BG)
ax.set_thetamin(0); ax.set_thetamax(180); ax.set_ylim(0, MAX_CM)
ax.set_rticks(np.linspace(MAX_CM / 4, MAX_CM, 4))
ax.yaxis.set_major_formatter(lambda v, _: f'{v:.0f} cm')
ax.grid(color=GRID, lw=0.8)
ax.spines['polar'].set_color(GRID)
ax.tick_params(colors=CYAN, labelsize=9)

sweep, = ax.plot([0, 0], [0, MAX_CM], color=CYAN, lw=2)
trail, = ax.fill([0, 0, 0], [0, 0, 0], color=CYAN, alpha=0.15, lw=0)
blips = ax.scatter([], [], s=45, edgecolors='none')
readout = fig.text(0.5, 0.08, 'Waiting for data...', ha='center',
                   color=CYAN, family='monospace', fontsize=13)

points, last_deg, direction = [], None, 1
base = np.array(to_rgba(CYAN))

while plt.fignum_exists(fig.number):
    lines = [ser.readline()]
    while ser.in_waiting:                      # catch up on any backlog
        lines.append(ser.readline())

    for raw in lines:                          # works for "45,23" or "Angle: 45 deg Distance: 23 cm"
        nums = re.findall(r'-?\d+(?:\.\d+)?', raw.decode(errors='ignore'))
        if not nums:
            continue
        deg = float(nums[0])
        if last_deg is not None and deg != last_deg:
            direction = 1 if deg > last_deg else -1
        last_deg, rad = deg, math.radians(deg)

        if len(nums) > 1 and 0 < float(nums[1]) <= MAX_CM:
            dist = float(nums[1])
            points.append((rad, dist, time.time()))
            readout.set_text(f'{deg:3.0f}°   {dist:5.1f} cm')
        else:
            readout.set_text(f'{deg:3.0f}°   out of range')

    if last_deg is not None:
        rad = math.radians(last_deg)
        sweep.set_data([rad, rad], [0, MAX_CM])
        arc = np.linspace(rad - direction * TRAIL, rad, 20)
        trail.set_xy(np.column_stack([np.r_[arc, rad], np.r_[np.full(20, MAX_CM), 0]]))

    now = time.time()
    points = [p for p in points if now - p[2] < FADE_S]
    if points:
        th, r, t = map(np.array, zip(*points))
        cols = np.tile(base, (len(points), 1))
        cols[:, 3] = 1 - (now - t) / FADE_S
        blips.set_offsets(np.column_stack([th, r]))
        blips.set_facecolors(cols)
    else:
        blips.set_offsets(np.empty((0, 2)))

    plt.pause(0.001)

ser.close()
