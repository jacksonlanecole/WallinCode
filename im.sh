g++ -Wall image_creator/im.cpp image_creator/Galaxy_Class.cpp -o image.out -ggdb `pkg-config --cflags --libs opencv`
./image.out image_creator/im.config image_creator/im.param