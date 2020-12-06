.PHONY: all
all: task1 task2

task1:  
	g++ prefix_table.cpp Tree.cpp -o prefix_table

task2:
	g++ prefix_table_opt.cpp Tree.cpp -o prefix_table_opt

.PHONY: clean
clean:
	-rm prefix_table prefix_table_opt 2>/dev/null