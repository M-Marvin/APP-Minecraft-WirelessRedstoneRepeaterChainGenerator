# APP-Minecraft-WirelessRedstoneRepeaterChainGenerator
A tool to generate a prioritiy list of repeater configurations.

Simply type "gen *number of available repeaters*" and the programm calculates a exact list of the possible configurations.

The list automaticaly selects the delay that has the most possible configurations.
The configuration on top of the list gets calculated first and the one on the bottem at last (when build in minecraft).

The number of repeaters is not limited, but somewhere by 15 or 20 the list gets so long that it can't be displayed completely in the console.
Also the time for the calculations and the used RAM increases exponentialy if to large numbers are entered.
I meassured around 10 seconds on with 40 repeaters.

NOTE: There is currently a weird bug that causes the programm to find no results when using exactly 30 repeaters.
Did not spent time to solva that, since i can not think there is any case in which you need that many repeaters ...
