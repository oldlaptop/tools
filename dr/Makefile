default: dr

clean:
	rm dr

test:
	@echo "testing random distribution for d10; all values should be close to 100"
	sh ./test.sh

	@echo
	@echo "testing random distribution for 2d5; should peak at 6"
	env DR_ARG=2d5 sh ./test.sh
