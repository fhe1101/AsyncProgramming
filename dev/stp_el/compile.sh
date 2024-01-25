rm -f *o
rm -f stp_el
rm -f udp_client

gcc -g -c network_utils.c -o network_utils.o
gcc -g -c stp.c -o stp.o
gcc -g -c utils.c -o utils.o
gcc -g -c udp_client.c -o udp_client.o
gcc -g -c rt.c -o rt.o
gcc -g -c stp_el.c -o stp_el.o
gcc -g -c ../../event_loop.c -o event_loop.o
gcc -g -c ../../timerlib.c -o timerlib.o
gcc -g stp.o utils.o rt.o network_utils.o stp_el.o event_loop.o timerlib.o -o stp_el -lrt -lpthread
gcc -g udp_client.o network_utils.o utils.o -o udp_client -lpthread
