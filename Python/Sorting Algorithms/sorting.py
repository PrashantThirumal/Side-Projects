"""
Template for all the sorting algorithms
"""

'''
Necessary imports for visualizing the sorting algorithms
'''
import random
import time

'''
Insertion Sort Complexity
Big O: best = O(N), worst = O(N²)
'''


def insertion_sort(lst):
    # Traverse from beginning to end of list
    for i in range(1, len(lst)):
        val = lst[i]

        # Move elements that are greater than val to the index right after it
        compare = i - 1
        while compare > 0 and val < lst[compare]:
            lst[compare + 1] = lst[val]
            compare -= 1

        lst[compare + 1] = val

    return lst


'''
Selection Sort Complexity
Big O: best/worst = O(N²)
Does no more than n swaps, and thus is useful where swapping is very expensive.
'''


def selection_sort(lst):
    # Traverse from beginning to end of list
    for i in range(1, len(lst)):
        # Find min element
        minimum_index = i
        for j in range(i + 1, len(lst)):
            if lst[minimum_index] > lst[j]:
                minimum_index = j

        # Swap min element with first element
        lst[i], lst[minimum_index] = lst[minimum_index], lst[i]

    return lst


'''
Merge Sort Complexity
Big O: O(N log N)
Essentially is just divide and conquer
'''


def merge_sort(lst):
    # Find middle of list
    # Divide into two halves
    # Recursively sort left and right half

    if len(lst) > 1:
        middle_index = len(lst) // 2
        left = lst[:middle_index]
        right = lst[middle_index:]

        merge_sort(left)
        merge_sort(right)

        i = j = k = 0
        # Copy data into temporary lists
        while i < len(left) and j < len(right):
            if left[i] < right[i]:
                lst[k] = left[i]
                i += 1
            else:
                lst[k] = right[j]
                j += 1

            k += 1

        # Check if any elements were left
        while i < len(left):
            lst[k] = left[i]
            i += 1
            k += 1

        while j < len(right):
            lst[k] = right[j]
            j += 1
            k += 1

    return lst


'''
Heap Sort Complexity
Big O: O(N log N)
Worst case complexity
'''


def heapify(lst, n, i):
    # Initialize largest as root
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    # Check if left child of root exits and is > root
    # Do the same for right child of root
    if left < n and lst[i] < lst[left]:
        largest = left
    if right < n and lst[largest] < lst[right]:
        largest = right

    # Change root if necessary
    if largest != i:
        lst[i], lst[largest] = lst[largest], lst[i]

        # Heapify the root
        heapify(lst, n, largest)


# Actual function to heap sort
def heap_sort(lst):
    n = len(lst)

    # Build a maxheap
    for i in range(n, -1, -1):
        heapify(lst, n, i)

    # Individually extract elements
    for i in range(n - 1, 0, -1):
        lst[i], lst[0] = lst[0], lst[i]
        heapify(lst, i, 0)
    return lst


'''
Quick Sort Complexity
Big O: best = O(N log N), worst O(N²)
Somewhat similar to merge sort
'''


# Partition helper method
def partition(lst, low, high):
    # Get index of smaller element and value of pivot
    i = (low - 1)
    pivot = lst[high]

    for j in range(low, high):
        # If current element is <= pivot increment index of smaller element
        if lst[j] < pivot:
            i = i + 1
            lst[i], lst[j] = lst[j], lst[i]

    lst[i + 1], lst[high] = lst[high], lst[i + 1]
    return i + 1


# Actual function to do Quick Sort
def quick_sort(lst, low, high):
    if low < high:
        # part is partitioning index, lst[p] is now at right place
        part = partition(lst, low, high)

        # Separately sort element before and after partition
        quick_sort(lst, low, part - 1)
        quick_sort(lst, part + 1, high)
    return lst


lst = [random.randint(0, 1000) for i in range(1000)]

print("Current list")
for x in range(len(lst)):
    print(str(x) + ": " + str(lst[x]))

print("============================================================")
print("\nSorting using insertion sort")
start = time.time()
ins_sort_lst = insertion_sort(lst)
end = time.time()
print("\nTime taken(s): " + str(end - start))
print("============================================================")


print("\nSorting using selection sort")
start1 = time.time()
sel_sort_lst = selection_sort(lst)
end1 = time.time()
print("\nTime taken(s): " + str(end1 - start1))
print("============================================================")

print("\nSorting using merge sort")
start2 = time.time()
merge_sort_lst = merge_sort(lst)
end2 = time.time()
print("\nTime taken(s): " + str(end2 - start2))
print("============================================================")

print("\nSorting using heap sort")
start3 = time.time()
heap_sort_lst = heap_sort(lst)
end3 = time.time()
print("\nTime taken(s): " + str(end3 - start3))
print("============================================================")

print("\nSorting using quick sort")
start4 = time.time()
quick_sort_lst = quick_sort(lst, 0, len(lst)-1)
end4 = time.time()
print("\nTime taken(s): " + str(end4 - start4))
print("============================================================")
