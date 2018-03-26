g++ -ggdb difference_code/diff.cpp -o diff.out `pkg-config --cflags --libs opencv`
./diff.out output/587722984435351614/ output/587722984435351614/targets/587722984435351614.calibrated.png output/587722984435351614/targets/587722984435351614.info.txt
