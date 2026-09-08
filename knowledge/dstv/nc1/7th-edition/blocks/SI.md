# DSTV 7th Edition - SI Block

## Source

DSTV 7th Corrected Edition, p. 12.

## Purpose

`SI` describes piece numeration/identification marking.

## Data

A numbering record contains:

- reference face;
- absolute X and Y;
- angle;
- text height;
- text to write;
- optional text-direction/parameter handling flags.

## Important flags

- `r` = text follows the piece if turned
- blank = text remains at same position
- `z` = force all parameters

If one or more parameters are not performed, the numeration is not performed.

SI is a separate marking function. Its absence is not automatically a specification error when piece numeration is not required.
