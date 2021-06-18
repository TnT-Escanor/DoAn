FROM cpp:latest

COPY . /home/tnt/DoAn_DucNguyenAnh

WORKDIR /home/tnt/DoAn_DucNguyenAnh

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install gcc &&\
    apt-get -y install g++ &&\
    apt-get -y install cmake &&\
    apt-get install build-essential

RUN cmake -Hcalculator_back-end -Bcalculator_back-end/build; \
    cmake --build calculator_back-end/build --target all --config Release; \
    calculator_back-end/build/CalculatorAPI

CMD ["./calculator_back-end/build/CalculatorAPI"] 