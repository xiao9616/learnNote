public class Sloution {

    public int numberOfSteps (int num) {
        int step=0;
        while(num!=0){
            num = (num & 1) == 0 ? num>>1 : --num ;
            ++step;
        }
        return step;
    }
}

class Solution {
    public:
    int numberOfSteps (int num) {
        int step=0;
        while(num){
            num = (num & 1) == 0 ? num>>1 : --num ;
            ++step;
        }
        return step;
    }
};