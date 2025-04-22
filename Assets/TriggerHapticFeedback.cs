using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class TriggerHapticFeedback : MonoBehaviour
{

    public enum Hand
    {
        right,
        left
    };


    public enum Finger
    {
        index,
        pointer,
        middle,
        ring,
        pinky
    };

    public Hand hand;
    public Finger finger;

    void Start()
    {
        Debug.Log("Script Awake");
        // StartCoroutine(SendData());
    }

    // Method called when the collider first touches another collider
    private void OnTriggerEnter(Collider other)
    {
        Debug.Log(finger.ToString() + " finger of the " + hand.ToString() + " hand has started colliding with the cube!");
        // Add any specific actions you want to happen when the collision starts
       StartCoroutine(SendData1());
    }

    // Method called once per frame for every frame the collider stays touching another collider
    private void OnTriggerStay(Collider other)
    {
        Debug.Log(finger.ToString() + " finger of the " + hand.ToString() + " hand is continuously colliding with the cube!");
        // Add any specific actions you want to continue happening as long as the collision continues
    }

    // Method called when the collider stops touching another collider
    private void OnTriggerExit(Collider other)
    {
        Debug.Log(finger.ToString() + " finger of the " + hand.ToString() + " hand has stopped colliding with the cube!");
        // Add any specific actions you want to happen when the collision ends
      //  StartCoroutine(SendData2());
    }
    IEnumerator SendData1()
    {
        string dataToSend = "r";
        Debug.Log("running function");
        string url = "http://192.168.0.194/receiveData";

        WWWForm form = new WWWForm();
        form.AddField("data", dataToSend);

        UnityWebRequest request = UnityWebRequest.Post(url, form);
        yield return request.SendWebRequest();

        if (request.result != UnityWebRequest.Result.Success)
        {
            Debug.LogError("Error sending data: " + request.error);
        }
        else
        {
            Debug.Log("Data sent successfully");
        }
    }

       IEnumerator SendData2()
    {
        string dataToSend = "Finger Touch Ended";
        Debug.Log("running function");
        string url = "http://192.168.0.194/";

        WWWForm form = new WWWForm();
        form.AddField("data", dataToSend);

        UnityWebRequest request = UnityWebRequest.Post(url, form);
        yield return request.SendWebRequest();

        if (request.result != UnityWebRequest.Result.Success)
        {
            Debug.LogError("Error sending data: " + request.error);
        }
        else
        {
            Debug.Log("Data sent successfully");
        }
    }
}
