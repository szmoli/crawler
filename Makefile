# config
out_dir := out
src_dir := src
conf_dir := conf
CC := gcc
out_name := build.out

# rules
build: $(wildcard $(src_dir)/*.c)
	$(CC) $^ -o $(out_dir)/$(out_name)

run:
	$(out_dir)/$(out_name)

clean:
	rm -rf $(out_dir)/*