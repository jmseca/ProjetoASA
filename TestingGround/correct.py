# Este ficheiro é código que está online, que em princípio está correto
# Usarei o Output deste ficheiro para perceber que possíveis erros posso ter

def lis(arr):
    n = len(arr)
  
    # Declare the list (array) for LIS and initialize LIS
    # values for all indexes
    lis = [1]*n
  
    # Compute optimized LIS values in bottom up manner
    for i in range (1, n):
        for j in range(0, i):
            if arr[i] > arr[j] and lis[i]< lis[j] + 1 :
                lis[i] = lis[j]+1
  
    # Initialize maximum to 0 to get the maximum of all
    # LIS
    maximum = 0
  
    # Pick maximum of all LIS values
    for i in range(n):
        maximum = max(maximum, lis[i])
  
    return maximum
# end of lis function
  
def findNumberOfLIS(nums):
 
    # Base Case
    if not nums:
        return 0
 
    n = len(nums)
 
    # Initialize dp_l array with 1s
    dp_l = [1] * n
 
    # Initialize dp_c array with 1s
    dp_c = [1] * n
 
    for i, num in enumerate(nums):
        for j in range(i):
 
            # If current element is smaller
            if nums[i] <= nums[j]:
                continue
 
            # Otherwise
            if dp_l[j] + 1 > dp_l[i]:
                dp_l[i] = dp_l[j] + 1
                dp_c[i] = dp_c[j]
 
            elif dp_l[j] + 1 == dp_l[i]:
                dp_c[i] += dp_c[j]
 
    # Store the maximum element from dp_l
    max_length = max(x for x in dp_l)
 
    # Stores the count of LIS
    count = 0
 
    # Traverse dp_l and dp_c simultaneously
    for l, c in zip(dp_l, dp_c):
 
        # Update the count
        if l == max_length:
            count += c
 
    # Return the count of LIS
    return count

# Driver program to test above function

exercise = str(input(""))
arr_str = str(input(""))



arr = list(map(int, arr_str.split()))
arr2 = list(map(int, arr_str.split()))


#print("Size = "+str(len(arr)))
 
# Function Call
# arr = [10, 22, 9, 33, 21, 50, 41, 60]
#print("Number of LIS: "+str(findNumberOfLIS(arr)))
 
 
# Driver program to test the above function
#n = len(arr)
#print ("Length of lis is "+lis(arr))

#max,hMany
print(lis(arr),findNumberOfLIS(arr2))