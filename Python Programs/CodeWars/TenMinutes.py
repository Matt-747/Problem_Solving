def is_valid_walk(walk):
    if len(walk) != 10: # if the array is less or bigger than 10, since each element takes 1 minute
        return False
    
    else: # If the array takes 10 minutes, it has to lead back to the starting point
        # Count the number of each direction, since it can only get back to the start if count_n = count_s and count_w = count_e
        count_n = 0
        count_s = 0
        count_e = 0
        count_w = 0

        for i in range(10): # Checks in the array if the number of symmetric directions is equal
            if walk[i] == 'n':
                count_n += 1

            elif walk[i] == 's':
                count_s += 1

            elif walk[i] == 'e':
                count_e += 1    

            elif walk[i] == 'w':
                count_w += 1

        if (count_n != count_s) or (count_e != count_w): # If the conditions are not satisfied, returns false
            return False

        else:
            return True
