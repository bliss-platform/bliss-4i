valgrind --tool=memcheck \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --error-limit=no \
         ./release
         
valgrind --tool=helgrind --history-level=full ./release
valgrind --tool=drd ./release

valgrind --tool=callgrind ./release
kcachegrind callgrind.out.*

valgrind --tool=cachegrind ./release