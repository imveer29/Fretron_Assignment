// Fully Working Code

// Website used for c++ reference : https://cplusplus.com/


#include <bits/stdc++.h>
using namespace std;

void recursion(int idx, vector<int> &ram, vector<int> &sham, vector<int> &rahim, vector<int> &amount, vector<pair<int, vector<vector<int>>>> &allDistributions) {
	// idx depicts the current amount arrays index
	if (idx == -1) {
		// calculation total amount of apples recieved by ram , sham and rahim and also the total amount of given apples;
		int totalAmountRam = accumulate(ram.begin(), ram.end(), 0);
		int totalAmountSham = accumulate(sham.begin(), sham.end(), 0);
		int totalAmountRahim = accumulate(rahim.begin(), rahim.end(), 0);
		int totalAmountApples  = accumulate(amount.begin(), amount.end(), 0);

		// calculation proportion of apples recieved by ram , sham and rahim
		int ramsProportion = (totalAmountRam * 100) / totalAmountApples;
		int shamsProportion = (totalAmountSham * 100) / totalAmountApples;
		int rahimProportion = (totalAmountRahim * 100) / totalAmountApples;

		// calculating diffrence between requried proportion and proportion of the current distribution
		int diff = abs(ramsProportion - 50) + abs(shamsProportion - 30) + abs(rahimProportion - 20);
		allDistributions.push_back({diff, {ram, sham, rahim}});
		return;
	}

	ram.push_back(amount[idx]); // giving current apple to ram
	recursion(idx - 1, ram, sham, rahim, amount, allDistributions); //recursion call for remaining apples
	ram.pop_back(); //restores the previous state (backtrack)

	sham.push_back(amount[idx]); // giving current apple to sham
	recursion(idx - 1, ram, sham, rahim, amount, allDistributions); // recursion call for remaining apples
	sham.pop_back();// restores the previous state (backtrack)

	rahim.push_back(amount[idx]);// giving current apple to rahim
	recursion(idx - 1, ram, sham, rahim, amount, allDistributions); // recursion call for remaining apples
	rahim.pop_back(); // resotres the previous state (backtrack)
}
int main() {

	int number_of_apples;
	cin >> number_of_apples;

	vector<int> amount(number_of_apples);
	for (int i = 0; i < number_of_apples; ++i) {
		cin >> amount[i];
	}

	vector<int> ram, sham, rahim; // this will contain amounts of apples distributed among ram, sham and rahim during recursion calls
	vector<pair<int, vector<vector<int>>>> allDistributions; // this will contain difference between requried proportion and proportion of the current distribution

	recursion(number_of_apples - 1, ram, sham, rahim, amount, allDistributions); // recursion call

	sort(allDistributions.begin(), allDistributions.end()); // this will sort all distribution according to the difference between requried proportion and proportion of the current distribution in ascending order

	vector<vector<int>> ans = allDistributions[0].second; // first distribution will be the minimum one

	// Output
	cout << "Distribution Results" << endl;
	cout << endl;
	cout << "Ram: ";
	for (auto i : ans[0]) {
		cout << i << " ";
	} cout << endl;
	cout << "Sham: ";
	for (auto i : ans[1]) {
		cout << i << " ";
	} cout << endl;
	cout << "Rahim: ";
	for (auto i : ans[2]) {
		cout << i << " ";
	} cout << endl;
}