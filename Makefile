all:
	./build.sh

stm32f4_disco:
	west build -p auto -d build -b stm32f4_disco

upload:
	west flash -d build

flash:
	west flash -d build

clean:
	-rm -fr build
	-find . -name "*~" -exec rm {} \;
