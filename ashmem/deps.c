#include <linux/mm.h>
#include <linux/kallsyms.h>

typedef void* (*kallsyms_lookup_name_t)(const char *name);

extern kallsyms_lookup_name_t wrapped_kallsyms_lookup_name;

typedef int (*shmem_zero_setup_ptr_t)(struct vm_area_struct *);
static shmem_zero_setup_ptr_t shmem_zero_setup_ptr = NULL;
int shmem_zero_setup(struct vm_area_struct *vma)
{
	if (!shmem_zero_setup_ptr)
		shmem_zero_setup_ptr = (shmem_zero_setup_ptr_t) wrapped_kallsyms_lookup_name("shmem_zero_setup");
	return shmem_zero_setup_ptr(vma);
}

