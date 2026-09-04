def open_or_senior(data):
    results = [] # List of results

    for i in range(len(data)):
        if data[i][0] >= 55 and data[i][1] > 7: # If the player is 55 or older and his handicap is higher than 7
            results.append('Senior')

        else: # If the player is younger than 55 or his handicap is lower than 7, category is 'Open'
            results.append('Open')

    return results
