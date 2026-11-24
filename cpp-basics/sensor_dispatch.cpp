#include <cstdio>
#include <cstddef>
#include <cstring>

class Sensor {
    public:
        virtual ~Sensor(){
            std::printf("~Sensor\n");
        }

        virtual double read() const{
            return 0.0;
        }

        virtual const char *name() const{
            return "Sensor";
        }
};

class RangeSensor : public Sensor {
    private:
        double distance;
    public:

        RangeSensor(double dist) : distance(dist){}

        ~RangeSensor(){
            std::printf("~RangeSensor\n");
        }

        double read() const override{
            return distance;
        }

        const char *name() const override{
            return "RangeSensor";
        }
};

class TempSensor : public Sensor {
    private:
        double temperature;

    public:

        TempSensor(double temp) : temperature(temp){}

        ~TempSensor(){
            std::printf("~TempSensor\n");
        }

        double read() const override{
            return temperature;
        }

        const char *name() const override{
            return "TempSensor";
        }
};

double total(const Sensor* const* list, std::size_t n){

    double sum = 0.0;
    for(std::size_t i = 0; i < n; i++){
        sum += list[i]->read();
    }

    return sum;
}


int main(){
    Sensor b;
    RangeSensor r(2.5);
    TempSensor t(30.0), cold(-10.0);

    const Sensor *one_r[]  = {&r};
    const Sensor *one_t[]  = {&t};
    const Sensor *mixed[]  = {&r, &t};
    const Sensor *base[]   = {&b};
    const Sensor *neg[]    = {&t, &cold};

    struct TotalRow { const char *label; const Sensor *const *list; std::size_t n; double want; };
    TotalRow total_rows[] = {
        {"empty",     nullptr, 0, 0.0},
        {"one range", one_r,   1, 2.5},
        {"one temp",  one_t,   1, 30.0},
        {"mixed",     mixed,   2, 32.5},
        {"base only", base,    1, 0.0},
        {"negative",  neg,     2, 20.0},
    };

    struct NameRow { const char *label; const Sensor *s; const char *want; };
    NameRow name_rows[] = {
        {"name range", &r, "RangeSensor"},
        {"name temp",  &t, "TempSensor"},
        {"name base",  &b, "Sensor"},
    };


    int fails = 0;

    std::size_t len_total = sizeof(total_rows)/sizeof(total_rows[0]);
    for(std::size_t i = 0; i < len_total; i++){
        double res = total(total_rows[i].list, total_rows[i].n);
        if(res != total_rows[i].want){
            std::printf("FAILED : %s\n", total_rows[i].label);
            fails++;
            continue;
        }
        std::printf("OK : %s\n", total_rows[i].label);
    }

    std::size_t len_name = sizeof(name_rows)/sizeof(name_rows[0]);
    for(std::size_t i = 0; i < len_name; i++){
        const char *res = name_rows[i].s->name();
        if(std::strcmp(res, name_rows[i].want) != 0){
            std::printf("FAILED : %s\n", name_rows[i].label);
            fails++;
            continue;
        }
        std::printf("OK : %s\n", name_rows[i].label);
    }


    const Sensor *heap_sensors[] = {new RangeSensor(200.0), new TempSensor(36.57)};
    std::size_t len = sizeof(heap_sensors)/sizeof(heap_sensors[0]);
    double res = total(heap_sensors, len);
    std::printf("Sum of range and temp sensor readings: %.2f\n", res);

    for (std::size_t i = 0; i < len; ++i) {
        delete heap_sensors[i];
        heap_sensors[i] = nullptr;
    }

    return fails != 0;
}
