    #include<iostream>
    #include<set>
    #include<list>
    #include<map>
    #include<vector>
    #include<queue>
     
    struct Game {
        std::vector<int> requests;
        std::vector<std::list<int>> car_number_to_request_numbers;
        std::set<int> cars_on_floor;
        std::priority_queue<std::pair<int, int>> next_requests;
        int counter = 0;
        int max_floor_capacity;
        int max_request;
     
        Game(int number_of_cars, int max_cars_on_floor, int number_of_requests) {
            int car;
            car_number_to_request_numbers = std::vector<std::list<int>> (number_of_cars + 1);
            for(int i = 1; i <= number_of_requests ; ++i){
                std::cin>>car;
                requests.push_back(car);
                car_number_to_request_numbers[car].push_back(i);
            }
            max_floor_capacity = max_cars_on_floor;
            max_request = number_of_requests;
        }
     
        void make_a_move(int car, int req_number){
            if(cars_on_floor.find(car) != cars_on_floor.end()){
                car_number_to_request_numbers[car].pop_front();
                int next_request;
                if(car_number_to_request_numbers[car].empty()){
                    next_request = max_request + req_number;
                } else {
                    next_request = car_number_to_request_numbers[car].front();
                }
                next_requests.push(std::make_pair(next_request, car));
                return;
            }
     
            if(cars_on_floor.size() == max_floor_capacity){
                int car_to_delete = next_requests.top().second;
                cars_on_floor.erase(car_to_delete);
                next_requests.pop();
            }
     
            car_number_to_request_numbers[car].pop_front();
            int next_request;
            if(car_number_to_request_numbers[car].empty()){
                next_request = max_request + req_number;
            } else {
                next_request = car_number_to_request_numbers[car].front();
            }
            cars_on_floor.insert(car);
            next_requests.push(std::pair<int, int>(next_request, car));
            counter++;
        }
     
        void do_all_moves(){
            for(int i = 0; i < requests.size(); ++i){
                make_a_move(requests[i], i + 1);
            }
            std::cout<<counter;
        }
    };
     
    int main(){
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
     
        int number_of_cars, max_cars_on_floor, number_of_requests;
        std::cin >> number_of_cars >> max_cars_on_floor >> number_of_requests;
        Game game(number_of_cars, max_cars_on_floor, number_of_requests);
        game.do_all_moves();
    }
