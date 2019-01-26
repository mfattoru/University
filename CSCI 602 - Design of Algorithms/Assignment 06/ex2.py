#!/usr/bin/env python3

#suppose we have that all are ordered
def longestUnitInterval(nums):
    if(len(nums)==0):
        return 0
    setmax = nums[0]+1
    setsize=1
    for x in nums:
        if x > setmax:
            setmax = x+1
            setsize+=1
    return setsize

# def longestUnitInterval(nums):
#     if(len(nums)==0):
#         return 0
#     setmax = nums[0]+1
#     setsize=1
#     print("{ [",end=" ")
#     for x in nums:
#         if x > setmax:
#             print("], [",x,end=" ")
#             setmax = x+1
#             setsize+=1
#         else:
#             tempArr.append(x)
#             print(x,end=" ")
#     print("] }")
#     print("\nLongest set Interval: ",setsize)
#     return setsize

def getLongestUnitInterval(nums):
    if(len(nums)==0):
        return 0
    setmax = nums[0]+1
    tempArr = []
    finalList = []
    for x in nums:
        if x > setmax:
            finalList.append(tempArr)
            tempArr = [x]
            setmax = x+1
        else:
            tempArr.append(x)
    finalList.append(tempArr)
    return finalList


x = longestUnitInterval([0.7,1.0,1.5,2.0,2.3,2.6,3.1,3.6,3.9,4.2,4.7,5.2])
print("\nLongest set Interval: ",x)
y = getLongestUnitInterval([0.7,1.0,1.5,2.0,2.3,2.6,3.1,3.6,3.9,4.2,4.7,5.2])
print("Y: ",y)
