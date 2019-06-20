REQ=requirements.txt

.PHONY: all init install clean

all: init install

init:
	pip3 install -r $(REQ)

install:
	./setup.py install

test:
	./setup.py test

clean:
	rm -rf build dist model.egg-info