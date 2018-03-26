g++ -ggdb difference_code/diff_v2.cpp -o diff.out `pkg-config --cflags --libs opencv`
./diff.out output/587722984435351614/ output/587722984435351614/target_images/587722984435351614.calibrated.png
