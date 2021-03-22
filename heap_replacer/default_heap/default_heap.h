#pragma once

#include "main/util.h"

#include "light_critical_section/light_critical_section.h"

#include "cell_list.h"

class default_heap
{

private:

	cell_list* size_clist;
	cell_list** addr_clist;

	mem_cell** size_array;
	mem_cell*** addr_array;

	size_t** used_cells;

private:

	cell_desc* block_desc;

private:

	size_t used_size;
	size_t curr_size;
	size_t free_blocks;

private:

	light_critical_section critical_section;

public:

	default_heap();
	~default_heap();

private:

	size_t get_size_index(size_t size);
	size_t get_size_index(mem_cell* cell);
	size_t get_addr_index(void* address);
	size_t get_addr_index(mem_cell* cell);

	void add_size_array(mem_cell* cell);
	void add_addr_array(mem_cell* cell);

	void rmv_size_array(mem_cell* cell);
	void rmv_addr_array(mem_cell* cell);

	cell_node* insert_size_dlist(mem_cell* cell);
	cell_node* insert_addr_dlist(mem_cell* cell);

	void add_free_cell_size(mem_cell* cell);
	void add_free_cell_addr(mem_cell* cell);

	void rmv_free_cell(mem_cell* cell);

public:

	void add_free_cell(mem_cell* cell);
	mem_cell* get_free_cell(size_t size);

	size_t get_block_index(void* address);
	size_t get_block_index(mem_cell* cell);

	void add_used(mem_cell* cell);
	size_t rmv_used(void* address, size_t index);
	size_t get_used(void* address, size_t index);

private:

	size_t get_free_block_index(void* address);
	mem_cell* create_new_block();

public:

	size_t get_used_size() { return this->used_size; }
	size_t get_free_size() { return this->curr_size - this->used_size; }
	size_t get_curr_size() { return this->curr_size; }
	size_t get_free_blocks() { return this->size_clist->get_size(); }

	size_t get_addr_size_by_index(size_t index) { return this->used_cells[0u][index]; }

};
