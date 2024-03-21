<?php
namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\Routing\Attribute\Route;
use App\Repository\ProductRepository;
use Symfony\Component\HttpFoundation\Request;
use Doctrine\ORM\EntityManagerInterface;
use App\Entity\Product;
use Vich\UploaderBundle\Handler\DownloadHandler;

#[Route('/sw')]
class SwUpdaterController extends AbstractController {
    #[Route('/version')]
    public function showVersionAction(ProductRepository $repository): Response {
		$latest = $repository ->findOneBy( [], ['id' => 'DESC'] );
		if ( !$latest ) 
			return new Response( '', Response::HTTP_NOT_ACCEPTABLE ); // 406
		// Avoid "Transfer-Encoding: chunked"
		$json = json_encode( [ 'ver' =>$latest ->getVersion( ) ] );
		return new JsonResponse( $json, Response::HTTP_OK, [ 'Content-Length' =>\strlen( $json ) ], true );
	}
	
    #[Route('/update', methods: ['GET'])]
    public function downloadAction(ProductRepository $repository, DownloadHandler $downloadHandler): Response {
		$latest = $repository ->findOneBy( [], ['id' => 'DESC'] );
		if ( !$latest ) 
			return new Response( '', Response::HTTP_NOT_ACCEPTABLE ); // 406
		$response = $downloadHandler ->downloadObject( $latest, $fileField = 'imageFile' );
		// Avoid "Transfer-Encoding: chunked"
		$response ->headers ->set( 'Content-Length', $latest ->getImageSize( ) );
		return $response;
    }
	
    #[Route('/update', methods: ['POST'])]
    public function uploadAction(Request $request, EntityManagerInterface $entityManager): Response {
		$version = $request ->query ->get( 'ver' );
		if ( !$version )
			$version = $request ->headers ->get( 'Fw-Ver' );
		if ( !$version )
			$version = $request ->request ->get( 'ver' );
		if( !$version )
			return new Response( '', HTTP_EXPECTATION_FAILED );

        $file = $request ->files ->get( 'imageFile' );
		$firmware = new Product( );
		$firmware ->setImageFile( $file );
		$firmware ->setVersion( $version );
		$entityManager ->persist( $firmware );
		$entityManager ->flush( );
		return new Response( );
	}
	
}
