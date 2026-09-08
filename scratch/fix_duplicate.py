import re

filepath = r'C:\Users\ricog\3D Modeling\Inventor API work\scratch\dstv_exporter.vb'
with open(filepath, 'r', encoding='utf-8') as f:
    lines = f.readlines()

# Find and remove duplicate facePos blocks in rectangle section
# Lines 1454-1458 (first facePos) and 1459-1463 (duplicate facePos)
# We want to keep only the first one and the angle computation

# Find the pattern: two consecutive facePos blocks
output = []
skip_next_facepos = False
for i, line in enumerate(lines):
    if skip_next_facepos:
        # Check if this is the end of the duplicate block (holeZ))
        if 'holeZ)' in line:
            skip_next_facepos = False
            continue
        continue
    
    output.append(line)
    
    # Check if we just added a holeZ) line and the next lines are a duplicate facePos
    if 'holeZ)' in line and i + 1 < len(lines):
        # Look ahead to see if next line starts a facePos block
        # We need to check if this facePos block was just added (i.e., it's a duplicate)
        pass

# Actually, let me use a simpler approach - find the exact line numbers and remove them
# Lines are 0-indexed in the list
# Line 1459 is index 1458, line 1463 is index 1462

# Let me find the duplicate by looking for two consecutive facePos blocks
new_output = []
i = 0
while i < len(lines):
    line = lines[i]
    new_output.append(line)
    
    # Check if this line contains 'holeZ)' and the next line starts 'Dim facePos'
    if 'holeZ)' in line and i + 1 < len(lines):
        next_line = lines[i + 1]
        if 'Dim facePos As Double' in next_line:
            # Skip the duplicate facePos block (it should be 5 lines: facePos, GetFacePosition, sFace, holeY, holeZ)
            # But we need to check exact structure
            i += 1  # skip the Dim facePos line
            # Skip until we find the blank line after holeZ)
            while i < len(lines) and 'holeZ)' not in lines[i]:
                i += 1
            if i < len(lines):
                i += 1  # skip the holeZ) line
            continue
    
    i += 1

with open(filepath, 'w', encoding='utf-8') as f:
    f.writelines(new_output)

print("Fixed duplicate facePos blocks")
