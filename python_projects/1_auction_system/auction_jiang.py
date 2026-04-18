import random
import math

class Auction:
    """ The main second-price ad auction to be played """

    def __init__(self, users, bidders):
        """ The initializer for the Auction instance """

        # A list of all User objects
        self.users = users
        # A list of all Bidder objects
        self.bidders = bidders
        # A dictionary containing the current balance of every bidder
        self.balances = {bidder:0 for bidder in bidders}

    def execute_round(self) -> None:
        """ An execution of all steps of a single round """

        # 1. User chosen at random (equal prob), can repeat
        chosen_userID = random.randint(0,len(self.users)-1)

        # 2. Bidders place bids
        max_bid = 0
        second_max_bid = 0
        max_bid_bidders = []
        for i in range(len(self.bidders)):
            
            # Disqualify this Bidder from placing a bid
            if self.balances[self.bidders[i]] < -1000:
                continue

            bid = self.bidders[i].bid(chosen_userID)

            # (a) When the bidder place a bid with current max amount
            if math.isclose(max_bid, bid):
                # Format: (index, Bidder, bid)
                max_bid_bidders.append((i,self.bidders[i],bid))
            # (b) When the bidder place a bid between current max and second max amount
            elif (bid > second_max_bid) and (bid < max_bid):
                second_max_bid = bid
            # (c) When the bidder place a bid over the current max amount
            elif bid > max_bid:
                # Update max& second highest bids
                second_max_bid = max_bid
                max_bid = bid
                max_bid_bidders = [(i,self.bidders[i],bid)]

        # 3. Winner: one of the Bidders with the highest bid
        winner_id = max_bid_bidders[random.randint(0,len(max_bid_bidders)-1)][0]

        # 4. Winning price: the 2nd highest bid
        price = max_bid if (len(max_bid_bidders) > 1) else second_max_bid

        # 5. User click or not according to its secret prob
        click = self.users[chosen_userID].show_ad()

        # 6. Notify Bidders: winning status / price / clicking status (winner only)
        for i in range(len(self.bidders)):
            if i == winner_id:
                self.bidders[i].notify(True, price, click)
                # 7. Bidder balance update: click-price for winner, 0 for non-winners
                self.balances[self.bidders[i]] += (click - price)
            else:
                self.bidders[i].notify(False, price, None)

    def __repr__(self):
        """ Return auction object with users and qualified bidders """
        return self.users, [bidder for bidder,bid in self.balances if bid > -1000]

    def __str__(self):
        """ Return auction object with users and qualified bidders """
        return self.users, [bidder for bidder,bid in self.balances if bid > -1000]


class User:
    """ The users playing the auction game """

    def __init__(self):
        """ The initializer for the User instance """

        # The private probability attribte to determine if the user click on an ad
        self.__probability = random.uniform(0,1)

    def show_ad(self) -> bool:
        """ To determine wether the user click the ad """
        return random.random() < self.__probability

    def __repr__(self):
        """ Usere object with secret probability """
        return str(self.__probability)

    def __str__(self):
        """ User object with a secret likelihood of clicking on an ad """
        return str(self.__probability)