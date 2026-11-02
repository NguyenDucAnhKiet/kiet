#include <iostream>

int main() {
	int n;
	if (!(std::cin >> n) || n <= 0) {
		return 0;
	}

	int maximum;
	if (!(std::cin >> maximum)) {
		return 0;
	}

	for (int i = 1; i < n; ++i) {
		int value;
		std::cin >> value;
		if (value > maximum) {
			maximum = value;
		}
	}

	std::cout << maximum << '\n';
	return 0;
}
