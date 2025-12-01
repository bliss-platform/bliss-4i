if [ -d "build" ]; then
	rm -rf build
fi
mkdir build

## build packager
cd packager
if [ -d "build" ]; then
	rm -rf build
fi
mkdir build
dart compile exe ./lib/hello.dart -o ./build/packager
cd ..
cp ./packager/build/packager ./build/packager
rm -rf ./packager/build
## end packager build