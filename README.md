# SE3701-01_lab
## HW-2

'''
************************************************************************************************************************

function MaxArea(arr):
    return f(arr, 0, arr.size() - 1)
    
************************************************************************************************************************

************************************************************************************************************************
function f(arr, left, right):
    if left == right:
      return arr[left]
    
  mid = (left + right) / 2

  return max(f(arr, left, mid), f(arr, mid + 1, right), merge(arr, left, right, mid))
************************************************************************************************************************

************************************************************************************************************************
function merge(arr, left, right, mid):
    l = mid - 1
    r = mid + 1
    Max = arr[mid]
    Min = arr[mid]
    len = 1

    while l >= left && r <= right :
      len++
      if arr[l] >= arr[r]:
        Min = min(Min, arr[l--])
        Max = max(Max, Min * len)
      else :
        Min = min(Min, arr[r++])
        Max = max(Max, Min * len)

    while l >= left:
      len++
      Min = min(Min, arr[l--])
      Max = max(Max, len * Min)

    while r <= right:
      len++
      Min = min(Min, arr[r++])
      Max = max(Max, len * Min)

    return Max
    *****
  '''
      
