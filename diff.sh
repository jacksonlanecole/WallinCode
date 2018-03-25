g++ -ggdb difference_code/diff.cpp -o diff.out `pkg-config --cflags --libs opencv`
# The commented line was the line that worked originally. The line below that
## contains a third argument that specifies the target info path.
#./diff.out output/587722984435351614/ targets/587722984435351614/587722984435351614.calibrated.png
./diff.out output/587722984435351614/ targets/587722984435351614/587722984435351614.calibrated.png targets/587722984435351614/587722984435351614.info.txt
