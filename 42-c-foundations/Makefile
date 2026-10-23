SUBDIRS = libft ft_printf get_next_line
all:
	@set -e; for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done
bonus: all
	$(MAKE) -C get_next_line bonus
clean:
	@set -e; for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
	rm -rf tests/build
	rm -f read_lines
fclean:
	@set -e; for dir in $(SUBDIRS); do $(MAKE) -C $$dir fclean; done
	rm -rf tests/build
	rm -f read_lines
re:
	$(MAKE) fclean
	$(MAKE) all
test:
	python3 tests/run_tests.py
sanitize:
	python3 tests/run_tests.py --sanitize
.PHONY: all bonus clean fclean re test sanitize
