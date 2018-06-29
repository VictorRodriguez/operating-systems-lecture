# Slides for Return Oriented Programming talk

This is a simple awk script that generates images for a talk.

Lines starting with "code " are used to populate the code array.

Lines starting with "label " are used to set up labels in the assembly

There are a number of instructions, such as push, sp+=, call, read - inspect the animate.awk program to see them.

The command "draw" will output another image.

Typically make needs to be run twice, unless the number of images hasn't changed.

The makefile is pretty inefficient, it would be much better to only update the *.gv files if they have actually changed, which would then reduce the number of invocations of neato.

