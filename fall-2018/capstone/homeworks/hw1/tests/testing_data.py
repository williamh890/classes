from hypothesis import given, strategies as st, settings


def make_random_data():
    testing_data = []

    @given(st.lists(st.integers()))
    @settings(max_examples=500)
    def sorted_data(l):
        testing_data.append(l)

    sorted_data()

    testing_lists = '\n'.join([
        ' '.join(map(str, l)) for l in testing_data
    ])

    with open('testing_data.txt', 'w') as f:
        f.write(testing_lists)


if __name__ == "__main__":
    make_random_data()
