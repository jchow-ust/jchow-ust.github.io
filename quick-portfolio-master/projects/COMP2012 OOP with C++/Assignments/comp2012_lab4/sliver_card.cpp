#include "regular_card.h"
#include "silver_card.h"


//TODO: Implement the constructor here.
SilverCard::SilverCard(int id, string na, int coup) : RegularCard(id, na), number_of_coupons(5) {}

//TODO: Implement the get_number_of_coupons function here.
int SilverCard::get_number_of_coupons() const {
	return number_of_coupons;
}

//TODO: Print "Dear regular member {name},
//             remaining benefits are {get_credits} credits,
//                                    {number_of_cupons} coupons. ".
void SilverCard::check_member_benefits() const {
	cout << "Dear Silver member " << get_name() << "," << endl;
	cout << "remaining benefits are " << get_credits() << " credits," << endl;
	cout << "                       " << get_number_of_coupons() << " coupons." << endl;
}

//TODO: Exchange credits for coup coupons (5 credits for 1 coupon).
void SilverCard::exchange_credits_for_coupons(int coup) {
	if (coup <= 0) {
		cout << "SORRY, the input must be positive." << endl;
	} else {
		const int COUPON_CONVERT = 5;
		int available = (get_credits() - get_credits() % COUPON_CONVERT) / COUPON_CONVERT;
		if (available<coup){
			cout << "SORRY, not enough credits for " << coup << " coupons." << endl;
			cout << "You have " << get_credits() << " credits left and can only exchange for " << available << " coupons." << endl;
			return;
		}
		number_of_coupons += coup;
		set_credits(get_credits()-COUPON_CONVERT*coup);
	}
}

