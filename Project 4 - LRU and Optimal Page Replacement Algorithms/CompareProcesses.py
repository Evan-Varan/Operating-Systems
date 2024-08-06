# Notes
# Page is a chunk of virtual memory
# A page replacement algorithm is used to manage the contents of the physical memory.
# A page replacement algorithm happens when the operating system needs to load a page from virtual memory (disk) into physical memory (RAM), but there is no free space available in RAM.
# LRU (Least Recently Used) - When a page needs to be replaced, LRU selects the page that has not been used for the longest time.
# Optimal - When a page needs to be replaced, Optimal selects the page that will not be used for the longest period of time in the future.
# User Entered Frames represent the number of physical memory slots (page frames) available in the system's RAM.
# Reference string represents a series of page requests. Ex. [2, 1, 3, 4, 2, 1, 5, 6] represents requesting page 2, then page 1, then page 3, etc.

import random

page_possibilities = [1, 2, 3, 4, 5]
page_requests_length_possibilities = [10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
page_requests = [random.choice(page_possibilities) for _ in range(random.choice(page_requests_length_possibilities))]
print("Page requests:", page_requests, " with length ", len(page_requests))

frames = int(input("Enter number of frames:\n"))
physical_memory = []
pages_used = []
num_lru_faults = 0

# LRU Algorithm
print("\nRunning LRU Algorithm:\n")
for page in page_requests:
    if page not in physical_memory:
        num_lru_faults += 1
        if len(physical_memory) < frames:
            physical_memory.append(page)
            pages_used.append(page)
        else:
            last_used_page = pages_used[0]
            pages_used.remove(last_used_page)
            pages_used.append(page)

            index = physical_memory.index(last_used_page)
            physical_memory[index] = page
    else:
        pages_used.remove(page)
        pages_used.append(page)

    print("Pages Used:", pages_used)
    print("Physical Memory:", physical_memory)

# Clearing data structures and variables for the next algorithm
physical_memory.clear()
pages_used.clear()
num_opt_faults = 0

# Optimal Algorithm
print("\nRunning Optimal Algorithm:\n")
distance_index_list = []
for page in range(len(page_requests)):
    if page_requests[page] not in physical_memory:
        num_opt_faults += 1
        if len(physical_memory) < frames:
            physical_memory.append(page_requests[page])
        else:
            for physical_memory_slot in range(len(physical_memory)):
                cut_page_requests = page_requests[page:len(page_requests)]
                if physical_memory[physical_memory_slot] not in cut_page_requests:
                    distance_index_list.append(99)
                for distance_index in range(len(page_requests)):
                    if page_requests[distance_index] == physical_memory[physical_memory_slot] and distance_index > page:
                        distance_index_list.append(distance_index)
                        break
            max_value = max(distance_index_list)
            if max_value == 99:
                replace_value = distance_index_list.index(max_value)
                physical_memory[replace_value] = page_requests[page]
            else:
                replace_value = page_requests[max(distance_index_list)]
                replace_index = physical_memory.index(replace_value)
                physical_memory[replace_index] = page_requests[page]
            distance_index_list.clear()
    print("Physical Memory:", physical_memory)

print("\nLRU faults:", num_lru_faults)
print("Optimal faults:", num_opt_faults)
