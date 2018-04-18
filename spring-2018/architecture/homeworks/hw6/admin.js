
const main = () => {
    let { password } = expressRequest.query;

    if (password) {
        if (password !== 'beet') {
            return send(getWrapperHtml(getAdminLoginForm(getLoginError())));
        }

        mongo.findOne({auction: "data"}, onBidsFetched);
    } else {
        return send(getWrapperHtml(getAdminLoginForm()));
    };

}

const onBidsFetched = (err, auction) => {
    let { bids } = auction;
    const messages = [];

    if ('add' in expressRequest.query || 'remove' in expressRequest.query) {
        const { add, remove } = expressRequest.query;

        if (!!add) {
            bids[add] = getNewEmptyBid();
            const message = {
                style: 'success',
                text: `${add} has been added to the auction.`
            };

            messages.push(message);
        }
        if (!!remove && remove in bids) {
            delete bids[remove];

            const message = {
                style: 'warning',
                text: `${remove} has been removed from the auction.`
            };

            messages.push(message);
        }
    }

    return send(getWrapperHtml(getAllBids(bids, messages)));
};

const getNewEmptyBid = () => {
    return {
        "user": "none",
        "amount": -1
    };
}

const getLoginError = () => {
    return `<div class="alert alert-danger ">You are not the Minister we are looking for...</div>`
};

const getWrapperHtml = body => {
    return `
        <head>${getBootstrap()}</head>
        <body>
            <div style="width:50%; min-width:200px; margin:0 auto;">
                <h1>Prime Minister Login</h1>
                ${body}

                <hr>
                <form action="https://cloudstar.lawlorcode.com/wurst/wbhorn/root_veggie">
                    <input class="btn btn-primary" type="submit" value="Back To Auction">
                </form>
            </div>
        </body>
    `;
};

const getBootstrap = () => {
    return `
        <link
            rel="stylesheet"
            href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css"
            integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm"
            crossorigin="anonymous"
        >
    `;
};

const getAllBids = (bids, messages) => {
    let bidsHtml = ``;

    for (const veg in bids) {
        const {user, amount} = bids[veg];
        const bid = `
            <th scope="row">${veg}</th>
            <td>${user}</td>
            <td>${amount}</td>
        `;

        bidsHtml += `<tr>${bid}</tr>`;
    }

    const messagesHtml = getMessageHtml(messages);
    return `
        ${messagesHtml}
        <table class="table">
        <thead><tr>
            <th scope="col">Root</th>
            <th scope="col">Bidder IZ</th>
            <th scope="col">Amount</th>
        </tr></thead>
        <tbody>
            ${bidsHtml}
        </tbody>
        </table>
    `;
};

const getMessageHtml = messages => {
    let messagesHtml = ``;

    for (const message of messages) {
        const {style, text} = message;

        messagesHtml += `
            <div class="alert alert-${style} ">
                ${text}
            </div>
        `;
    }

    return messagesHtml;
};

const getAdminLoginForm = (err) => {
    return `
        ${!!err ? err : ""}
        <form action="?login">

          <div class="form-group">
              <label for="password">Password</label>
              <input
                  class="form-control"
                  type="password"
                  name="password"
                  placeholder="adminz only"
                  required
              >
          </div>
          <div class="form-group">
              <input class="btn btn-secondary" type="submit" value="Login">
          </div>

        </form>
    `;
};

main();

