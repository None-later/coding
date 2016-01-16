using System;
using System.Threading;

namespace CSharpPractice
{
    public class VideoEventArgs : EventArgs
    {
        public Video Video { get; set; }
    
    }
    public class VideoEncoder
    {
        // 1 : Define a delegate 
        // 2: Define an event based on the delegate
        // 3: Raise the event

        //public delegate void VideoEncodedEventHandler(object source, VideoEventArgs args);  //  1
        //public event VideoEncodedEventHandler VideoEncoded;   // 2

        // 1 and 2 can be replaced by one line below
        // EventHandler<>
        // EventHandler<TEventArg>
        public event EventHandler<VideoEventArgs> VideoEncoded;

        public void Encode(Video video)
        {
            Console.WriteLine("Encoding Video...");
            Thread.Sleep(3000);
            OnVideoEncoded(video);
        }

        // the convention : the enevt publisher should be protected, virtual and void return
        // 3 : raise the events
        protected virtual void OnVideoEncoded(Video video)
        {
            // notify subscribers 
            if (VideoEncoded != null)
                VideoEncoded(this, new VideoEventArgs(){ Video = video} );
        }
    }
}
