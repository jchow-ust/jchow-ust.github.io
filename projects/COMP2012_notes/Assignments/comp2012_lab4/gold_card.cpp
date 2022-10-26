#include "gold_card.h"

#include "silver_card.h"

//TODO: Implement the constructor here.
GoldCard::GoldCard(int id, string na, int coup, int tick) : SilverCard(id, na, coup), number_of_free_tickets(tick) {}

//TODO: Print "Dear regular member {name},
//            remaining benefits are {get_credits} credits,
//                                   {get_number_of_cupons} coupons,
//                                   {number_of_free_tickets} free tickets. ".
void GoldCard::check_member_benefits() const {
	cout << "Dear Gold member " << get_name() << "," << endl;
	cout << "remaining benefits are " << get_credits() << " credits," << endl;
	cout << "                       " << get_number_of_coupons() << " coupons," << endl;
	cout << "                       " << number_of_free_tickets << " free tickets." << endl;
}

//TODO: Exchange credits for tick free tickets (20 credits for 1 coupon).
void GoldCard::exchange_credits_for_free_tickets(int tick) {
	if (tick <= 0) {
		cout << "SORRY, the input must be positive." << endl;
	} else {
		const int TICKET_CONVERT = 20;
		int available = (get_credits() - get_credits() % TICKET_CONVERT) / TICKET_CONVERT;
		if (available<tick){
			cout << "SORRY, not enough credits for " << tick << " tickets." << endl;
			cout << "You have " << get_credits() << " credits left and can only exchange for " << available << " tickets." << endl;
			return;
		}
		number_of_free_tickets += tick;
		set_credits(get_credits()-TICKET_CONVERT*tick);
	}
}
