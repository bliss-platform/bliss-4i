valgrind --tool=memcheck \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --error-limit=no \
         ./debug
         
valgrind --tool=helgrind --history-level=full ./debug
valgrind --tool=drd ./debug

valgrind --tool=callgrind ./debug
kcachegrind callgrind.out.*

valgrind --tool=cachegrind ./debug