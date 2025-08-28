import random

class Bidder:
    """ A Bidder object to decide which ad to be shown to the user """

    def __init__(self, num_users, num_rounds):
        """ The initializer for the Bidder instance """

        # Number of User objects to be contained in the game
        self.num_users = num_users
        # Total number of rounds to be played
        self.num_rounds = num_rounds

        # To store the balance of the bidder
        self.__balance = 0
        # To store the user to place a bid to
        self.__last_bid_user = None
        # To store the notification results for each user (by id)
        self.__notif_records = {id:[] for id in range(num_users)}

    def bid(self, user_id) -> float:
        """ To determine the bidding amount for the specified user
        Arg:
            user_id: the given user id for the user
        Return:
            a non-negative flaot indicating the amount of money (3 decimals)
        """
        
        # Record the user_id that the bidder place a bid on
        self.__last_bid_user = user_id

        history = self.__notif_records[user_id]

        # No record before
        if len(history) == 0:
            return round(random.uniform(0,1), ndigits=3)
        # Bidder tend to lose the auction, increase bid to win
        elif sum(history) == 0:
            return round(min(1, random.uniform(0,1) + 0.1), ndigits=3)
        # Bidder tend to not click on the ad, decrease the bid
        elif sum(history) < 0:
            return round(max(0, -(sum(history) / len(history)) - 0.1), ndigits=3)
        # Bidder tend to click on the ad, keep current average bid amount
        else:
            return round(1 - (sum(history) / len(history)), ndigits=3)


    def notify(self, auction_winner, price, clicked=None) -> bool:
        """ To digest the bidding result for the round
        Args:
            auction_winner: boolean of wether the Bidder won the auction
            price: the amount of second bid, which the winner pays
            clicked: boolean of wether the user clicked on the ad (only for the winner)
        Return:
            A winning status and the price earned
            (winning price will be deducted if the Bidder won)
        """

        # Update the balance and notification records if the bidder won
        if auction_winner:
            self.__balance += (clicked - price)
            self.__notif_records[self.__last_bid_user].append(clicked - price)
        # Append 0 even if the bidder lost
        else:
            self.__notif_records[self.__last_bid_user].append(0)
        
        return True

    def __repr__(self):
        """ disqualify the bidder from participating """
        return str(self.__balance > -1000)

    def __str__(self):
        """ showing the balance of the current Bidder """
        return str(self.__balance)