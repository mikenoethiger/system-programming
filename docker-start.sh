# delete old container if exists, ignore stdout/stderr
docker container rm -f syspr &>/dev/null
# -it attaches std streams to the container (type exit to exit the container)
# -v maps the host working directory /home/syspr in the container, such that all files/folder are synced between host/container
# -w changes the working directory of the container to /home/syspr upon start
# --rm deletes the container after exit
docker run -it -v `pwd`:/home/syspr -w /home/syspr --name syspr --rm syspr bash