package oversim.applications.i3.i3Apps;

import oversim.common.ITier;


simple I3TRTServer
{
    parameters:
        bool debugOutput;
        int triggerTimeToLive;
        int serverPort;

    gates:
        input from_overlay;
        output to_overlay;
        input appIn;
        output appOut;
        input udpIn;
        output udpOut;
}

simple I3TRTClient like ITier
{
    parameters:
        int clientPort;
        int serverPort;
        double sampleRefreshTime @unit(s);
        double triggerRefreshTime @unit(s);
        double bootstrapTime @unit(s);
        double initTime @unit(s);
        int cacheSize;
        volatile double serverTimeout @unit(s);
        double idStoreTime @unit(s);
        volatile double triggerDelay @unit(s);
    gates:
        input udpIn;
        input from_lowerTier;
        input from_upperTier;
        output udpOut;
        output to_lowerTier;
        output to_upperTier;
}

