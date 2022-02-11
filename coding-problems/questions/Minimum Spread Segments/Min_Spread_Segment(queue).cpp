#include <bits/stdc++.h>

using namespace std;


struct min_queue {
	stack<pair<long long, long long>> s2, s1;


	long long getMin() {
		long long minimum;
		if (s1.empty() || s2.empty())
			minimum = s1.empty() ? s2.top().second : s1.top().second;
		else
			minimum = min(s1.top().second, s2.top().second);
		return minimum;
	}

	void push(long long new_element) {
		long long minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
		s1.push({new_element, minimum});
	}

	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				long long element = s1.top().first;
				s1.pop();
				long long minimum = s2.empty() ? element : min(element, s2.top().second);
				s2.push({element, minimum});
			}
		}
		s2.pop();
	}
};

struct max_queue {
	stack<pair<long long, long long>> s2, s1;


	long long getMax() {
		long long maximum;
		if (s1.empty() || s2.empty())
			maximum = s1.empty() ? s2.top().second : s1.top().second;
		else
			maximum = max(s1.top().second, s2.top().second);
		return maximum;
	}

	void push(long long new_element) {
		long long maximum = s1.empty() ? new_element : max(new_element, s1.top().second);
		s1.push({new_element, maximum});
	}

	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				long long element = s1.top().first;
				s1.pop();
				long long maximum = s2.empty() ? element : max(element, s2.top().second);
				s2.push({element, maximum});
			}
		}
		s2.pop();
	}
};


int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

	int n;
	long long k , ans = 0;
	cin >> n >> k;

	vector<long long> a(n);

	for (auto&e : a)
		cin >> e;

	int l = 0 , r = 0;

	max_queue mx_q;
	min_queue mn_q;

	while (r < n) {
		mx_q.push(a[r]);
		mn_q.push(a[r]);
		r++;

		while (mx_q.getMax() - mn_q.getMin() > k) {
			mx_q.pop();
			mn_q.pop();
			l++;
		}

		ans += (long long)(r - l);
	}

	cout << ans << "\n";
	return 0;
}