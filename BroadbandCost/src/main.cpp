#include <iostream>
#include <string>
#include "Timer/Timer.h"
#include <cmath>  // For std::abs


double calculatePercentageDifference(double originalValue, double newValue)
{
    if (originalValue == 0) {
        std::cerr << "Error: original value cannot be zero when calculating percentage difference." << std::endl;
        return 0.0;
    }

    double difference = newValue - originalValue;
    double percentDifference = (difference / originalValue) * 100.0;
    return percentDifference;  // Positive if increase, negative if decrease
}

double calculateInternetCost(
    int contractStartMonth,
    int contractLengthMonths,
    double initialPricePerMonth,
    double discountAmount,
    int discountDurationMonths,
    double inflationValue,
    bool useFlatInflation = true,  // Switch between % or flat £ increase
    int inflationMonth = 3,       // April by default
    double setupCharge = 0.0      // Setup fee, default £0
)
{
    double totalCost = setupCharge;  // Start with the setup fee
    double currentMonthlyPrice = initialPricePerMonth;
    bool inflationAppliedThisYear = false;
    bool billChanged = false;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Original monthly price before discount: GBP " << initialPricePerMonth << "\n";
    
    // First month price with discount
    double firstMonthPrice = initialPricePerMonth - discountAmount;
    //std::cout << "Month 1 (with discount): GBP " << firstMonthPrice << "\n";
    /*
    for (int month = contractStartMonth; month <= contractLengthMonths + contractStartMonth - 1; ++month) {
        

#if 1
        // Apply inflation every March (if not already applied this contract year)
        if (month % 12 == inflationMonth % 12 && !inflationAppliedThisYear) {
            if (useFlatInflation) {
                currentMonthlyPrice += inflationValue;  // Flat £ increase
            }
            else {
                currentMonthlyPrice *= (1 + inflationValue / 100.0);  // % increase
            }
            
            inflationAppliedThisYear = true; 
            billChanged = true;

            // std::cout << "Month " << month << ": Price updated due to inflation -> GBP " << billedPrice << "\n";
        }
#else
        int billingMonth = (contractStartMonth + month - 1) % 12;
        if (billingMonth == 0) billingMonth = 12;

        if (billingMonth == inflationMonth && !inflationAppliedThisYear) {
            if (useFlatInflation) {
                currentMonthlyPrice += inflationValue;
            }
            else {
                currentMonthlyPrice *= (1 + inflationValue / 100.0);
            }

            //std::cout << "Month " << month << ": Inflation applied -> new price: GBP "
            //   << billedPrice << (useFlatInflation ? " (flat GBP)" : " (%)") << "\n";

            inflationAppliedThisYear = true;
            billChanged = true;
        }
#endif
        // Apply discount if within discount period
        double billedPrice = (month <= discountDurationMonths)
            ? currentMonthlyPrice - discountAmount
            : currentMonthlyPrice;

        totalCost += billedPrice;

        if (inflationAppliedThisYear == true && billChanged == true)
        {
		    // Output the change in the billed price for the month
            std::cout << "Month " << month << ": Price updated due to inflation -> GBP " << billedPrice << "\n";
			billChanged = false;  // Reset the flag after outputting the change
        }
        else
		    // Output the billed price for the month
            std::cout << "Month " << month << ": Price -> GBP " << billedPrice << std::endl;

        // Reset inflation flag for the next year
        if (month % 12 == 0) {
            inflationAppliedThisYear = false;
        }
    }
    */

    for (int month = 1; month <= contractLengthMonths; ++month) {
        int billingMonth = (contractStartMonth + month - 1) % 12;
        if (billingMonth == 0) billingMonth = 12;

        if (billingMonth == inflationMonth && !inflationAppliedThisYear) {
            if (useFlatInflation) {
                currentMonthlyPrice += inflationValue;
            }
            else {
                currentMonthlyPrice *= (1 + inflationValue / 100.0);
            }

            inflationAppliedThisYear = true;
            billChanged = true;
        }

        double billedPrice = (month <= discountDurationMonths)
            ? currentMonthlyPrice - discountAmount
            : currentMonthlyPrice;

        totalCost += billedPrice;

        if (billChanged) {
            std::cout << "Month " << month << ": Price updated due to inflation -> GBP " << billedPrice << "\n";
            billChanged = false;
        }
        else {
            std::cout << "Month " << month << ": Price -> GBP " << billedPrice << "\n";
        }

        // Reset for next year
        if (billingMonth == 12) {
            inflationAppliedThisYear = false;
        }
    }


    return totalCost;
}

int main()
{
	// Vodafone broadband contract example
#if 0
    int contractStartMonth = 1;
    int contractMonths = 24;
    double initialPrice = 51.0;
    double discount = 19.0;
    int discountPeriod = 24;
    double inflation = 7.9;
	bool useFlatInflation = false; // Use flat £ increase instead of percentage
    int inflationMonth = 4;
    double setupFee = 0.0;  // Change to e.g. 15.0 if there's a setup charge
    
#else
	// EE broadband contract example
    int contractStartMonth = 3;
    int contractMonths = 24;
    double initialPrice = 44.99;
    double discount = 5.0;
    int discountPeriod = 24;
    double inflation = 3;
	bool useFlatInflation = true; // Use flat £ increase instead of percentage
    int inflationMonth = 4;
    double setupFee = 0.0;  // Change to e.g. 15.0 if there's a setup charge
#endif

    double totalPaid = calculateInternetCost(contractStartMonth, contractMonths, initialPrice, discount, discountPeriod, inflation, useFlatInflation, inflationMonth, setupFee);
    std::cout << "Total broadband cost over " << contractMonths << " months (incl. setup): GBP " << totalPaid << std::endl;


	std::cout << "Calculating percentage difference from initial price (with discount) to 1st price increase: " << calculatePercentageDifference(34.53, 36.74) << "..." << std::endl;

	std::cin.get();
    return 0;
}
