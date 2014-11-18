def sortAndCount(ar, helper, start, end):
        if(start < end):
                mid = (start+end)/2
                x = sortAndCount(ar,helper,start,mid)
                y = sortAndCount(ar,helper,mid + 1,end)
                z = mergeAndCount(ar,helper,start,mid,end)
                return x + y + z
        return 0
        
def mergeAndCount(ar,helper,start,mid,end):
        
        for i in range(start, end+1):
                helper[i] = ar[i]
        helpL = start
        helpR = mid + 1
        arIndex = start
        numInvers = 0
        while(helpL <= mid and helpR <= end):
                if(helper[helpL] < helper[helpR]):
                        ar[arIndex] = helper[helpL]
                        helpL += 1
                else:
                        ar[arIndex] = helper[helpR]
                        helpR += 1
                       
                        numInvers += (mid + 1) - helpL
                arIndex += 1
        remain = mid - helpL 
        for i in range(remain+1):
                ar[arIndex + i] = helper[helpL + i]
        
        return numInvers
        
with open('Q5.txt') as fopen:
        ints = []
        for nums in fopen:
                ints.append(int(nums.strip()))
        helper = list(ints)
        print(sortAndCount(ints,helper,0,len(ints)-1))
