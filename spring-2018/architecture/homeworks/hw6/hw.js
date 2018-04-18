
class RootVeggieAuction {
    constructor() {
        this.veggies = [
            "Potato",
            "Onion",
            "Turnip",
            "Imported Turnip"
        ];

        this.limit = 100;
    }

    successMessageFor(bid, total) {
        const {user, amount } = bid;

        return `
            <div class="alert alert-success ">
                User ${user}, Thank you for you're bid.
                You just spend ${amount} and have ${100 - total} Izhk left
                to spend. Happy Bidding!
            </div>
        `;
    }

    getErrorMessage(bid) {
        return `
            <div class=" alert alert-danger">
                <b>VERBOTEN!!!</b> User ${bid.user}, you my friend are out of money...
            </div>
        `;
    }

    getPage(type, data) {
        let message = "";

        if (type === "good-bid") {
            message = this.successMessageFor(data.newBid, data.userTotal);
        } else if (type === "error") {
            message = this.getErrorMessage(data.newBid);
        } else if (type === "low-bid") {
            message = this.lowBidMessage(data.newBid, data.currentBid);
        } else if (type === "login-error") {
            message = this.getLoginError();
        }

        return `
        <head>${this.getBootstrap()}</head>
        <body>
            <div style="width:50%; min-width:200px; margin:0 auto;">
                <h1>Root Veggies On Sale, Hot and Fresh!</h2>
                ${message}

                ${this.getRootVegtablesList()} <br>

                <h3>Auction</h3>
                <hr/>
                ${this.getBidingForm()}
                ${this.getAdminLoginForm()}
            </div>
        </body>
        `;
    }


    getAdminLoginForm() {
        return `
        <h4>Prime Minister Login</h4>

                <hr/>
            <form action="https://cloudstar.lawlorcode.com/wurst/wbhorn/minister_login?login">

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
        `
    }

    lowBidMessage(bid, current) {
        return `
            <div class="alert alert-warning ">
                ${bid.amount} Izhk is to low of a bid. Current bid is ${current.amount} Izhk.
            </div>
        `;
    }

    getBids(bids) {
        return JSON.stringify(bids);
    }

    getBidingForm() {
        const form = `
            <form action="?bid">
                <div class="form-group">
                <lable>IZ Number</lable>
                  <input
                      class="form-control"
                      type="text"
                      name="user"
                      placeholder="IZ Number"
                      required
                      pattern="[0-9]{6}"
                  >
                </div>
                <div class="form-group">
                <lable>Root Vegtable</lable>
                  <input
                      class="form-control"
                      type="text"
                      name="root"
                      placeholder="Root Vegtable"
                      required
                      pattern="${this.veggieRegex()}"
                  >
                  </div>
                    <div class="form-group">
                      <input
                          class="form-control"
                          type="number"
                          min="0" max="100" step="0.01"
                          name="amount"
                          placeholder="Amount"
                          required
                          pattern="\d+"
                      >
                  </div>
                  <div class="form-group">
                      <input class="btn btn-primary" type="submit" value="Bid!">
                  </div>
            </form>
        `;

        return form;
    }

    getBootstrap() {
        return `
            <link
                rel="stylesheet"
                href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css"
                integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm"
                crossorigin="anonymous"
            >
        `;
    }

    veggieRegex() {
        let re = "";

        for (const veg of this.veggies) {
            re += `${veg}|`;
        }

        return re.slice(0, -1);
    }

    getRootVegtablesList() {
        let veggieList = "";

        for (const veg of this.veggies) {
            veggieList += this.getVeggie(veg);
        }

        return `
            <ul class="list-group">
                ${veggieList}
            </ul>
        `;
    }

    getVeggie(veggie) {
        return `<li class="list-group-item">${veggie}</li>`;
    }

    getEmptyBids() {
        let bids = {};

        for (const veg of this.veggies) {
            const bid = {user: "none", amount: 0}

            bids[veg] = bid;
        }

        return bids;
    }
}

const auction = new RootVeggieAuction();
const main = () => {
    if (!isMakingABid() && !loggingIn()) {
        return send(auction.getPage());
    }

    makeBid();
};

const loggingIn = () => !!expressRequest.query.password;

const isMakingABid = () => {
    const {user, amount, root} = expressRequest.query;

    return !!user && !!amount && !!root;
};

const makeBid = () => {
    mongo.findOne({auction: "data"}, onBidsFetched)
};

const onBidsFetched = (err, auctionData) => {
    try {
        let { bids } = auctionData;

        let {user, amount, root} = expressRequest.query;

        const newAmount = parseFloat(amount);
        const newBid = {user, amount: newAmount };

        if (!bids) {
            bids = auction.getEmptyBids();
        }

        for (const veg in bids) {
            bids[veg].amount = parseFloat(bids[veg].amount);
        }

        if (newAmount <= bids[root].amount) {
            const html = auction.getPage("low-bid", {
                bids, newBid, currentBid: bids[root]
            });

            return send(html);
        }

        let userTotal = newAmount;
        for (const checkBid of Object.values(bids)) {
            if (checkBid.user === user) {
                userTotal += checkBid.amount;
            }
        }

        if (userTotal >= auction.limit) {
            const errorPageHtml = auction.getPage("error", {
                bids, newBid
            });

            return send(errorPageHtml);
        }

        bids[root] = newBid;
        setBids(bids);

        const pageHtml = auction.getPage("good-bid", {
            bids, newBid, userTotal
        });

        return send(
            pageHtml
        );

    } catch(err) {
        return send(`${err}`);
    }
};

const setBids = (bids) => {
    mongo.updateOne(
        {auction:"data"},
        {$set: {auction:"data", bids}},
        {upsert:true}
    );
};


main();

