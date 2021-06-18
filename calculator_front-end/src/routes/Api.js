class Api {

    constructor(serviceAddress) {
        this.serviceAddress = serviceAddress;
    }

    makeURL(num, checked, string) {
        const resource = string + "/" + num + "/" + checked;
        return new URL(resource, this.serviceAddress);
    }

    calculate(num, checked, string, handler) {
        console.log(string, "qua chuoi")
        fetch(this.makeURL(num, checked, string))
        .then(res => res.json())
        .then((response)=> {
            handler(response["result"]);
          },
          (err)=> {
            handler(err);
            console.log(err);
          }
        );
    }
}

export default Api;