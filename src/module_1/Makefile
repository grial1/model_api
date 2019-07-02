REQ=requirements.txt

.PHONY: all init install clean

all: init install

init:
	python3.6 -m venv .
	bash -c "source ./bin/activate &&\
	bin/python3 -m pip install -r $(REQ) &&\
	deactivate"

install:
	bash -c "source ./bin/activate &&\
	sudo bin/python3 setup.py install &&\
	deactivate"

test:
	bash -c "source ./bin/activate &&\
	sudo bin/python3 setup.py test &&\
	deactivate"

clean:
	rm -rf build dist model.egg-info