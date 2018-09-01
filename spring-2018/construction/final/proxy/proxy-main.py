from dbconnection import DBConnection


def main():
    handle = DBConnection()

    queries = [
        "some",
        "sql",
        "queries",
        "here..."
    ]

    for query in queries:
        handle.add(query)

    handle.commit()

    print("\nDone")


if __name__ == "__main__":
    main()
