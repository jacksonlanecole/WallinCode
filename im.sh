g++ -Wall image_creator/im.cpp image_creator/Galaxy_Class.cpp -o im.out -ggdb `pkg-config --cflags --libs opencv`
./im.out image_creator/im.config image_creator/im.param
