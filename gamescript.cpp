using UnityEngine;
using UnityEngine.UI;

public class GameScript : MonoBehaviour
{
    public Text scoreText;
    public Text gameOverText;

    private int score = 0;
    private bool gameOver = false;

    void Start()
    {
        scoreText.text = "Score: " + score.ToString();
        gameOverText.enabled = false;
    }

    void Update()
    {
        if (gameOver)
            return;

        if (Input.GetButtonDown("Fire1"))
        {
            RaycastHit hit;

            if (Physics.Raycast(transform.position, transform.forward, out hit))
            {
                if (hit.collider.gameObject.CompareTag("Enemy"))
                {
                    Destroy(hit.collider.gameObject);
                    score++;
                    scoreText.text = "Score: " + score.ToString();
                }
            }
        }

        if (score >= 10)
        {
            gameOver = true;
            gameOverText.enabled = true;
        }
    }
}
