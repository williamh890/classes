from hypothesis import given, strategies as st, settings


def make_random_data():
    testing_data = []

    integer_lists = st.lists(
        st.integers(min_value=-2147483647, max_value=2147483647)
    )

    @given(integer_lists)
    @settings(max_examples=500)
    def generate_testing_data(l):
        # Usually the test would just go here, but c++...
        testing_data.append(l)

    generate_testing_data()

    testing_lists = '\n'.join([
        ' '.join(map(str, l)) for l in testing_data
    ])

    with open('testing_data.txt', 'w') as f:
        f.write(testing_lists)


if __name__ == "__main__":
    make_random_data()
