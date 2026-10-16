
# Time syncronization

When Internet is available, NTP is ubiquitious.
When GPS/GNNS is available, that can be used.

If both GNSS and Internet is unavailable, one needs other methods of time syncronization.

Many protocols, radio and computer systems rely on accurate time-keeping.
Second-level precision is required in many cases.

FT8 / FT4 needs clocks to be within roughly 1 s of UTC to decode.
Similar for JT65 / JT9 / WSPR.

## Low-frequency radio clock
https://www.cl.cam.ac.uk/~mgk25/time/lf-clocks/

### DCF77 in Germany
https://www.hopf.com/about-dcf77_en.php

### ALS162 in France
https://alpem.dev/posts/als162_rx_part1/

## RDS (FM broadcast)

RDS carries a Clock-Time (CT) message (group 4A) with UTC date, time, and local offset.
Resolution is one minute, with no seconds.
The spec says the message should mark the minute edge, but the actual accuracy depends on the broadcaster’s equipment and processing delay.
