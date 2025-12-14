IMAGE_NAME=mewhere-ci

docker-install-dev:
	docker build -t ${IMAGE_NAME} --progress tty .

docker-dev-cli:
	docker container run \
		--rm -it --privileged \
		-v ${PWD}:/app \
		${IMAGE_NAME}
