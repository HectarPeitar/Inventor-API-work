using System;
using System.Runtime.InteropServices;
using Inventor;

namespace CustomCommand
{
	internal class RackFaceRequest : CustomCommand.ChangeRequest
	{
		//Inventor application object
		private Application m_application;

		//rack face command parameters
		private Face m_rackFace;
		private Edge m_rackEdge;

		private int m_noTeeth;
		private double m_rackHeight;
		private double m_rackWidth;
		private double m_rackExtents;
		private PartFeatureExtentDirectionEnum m_rackFeatureExtentDirection;	
		
		public RackFaceRequest (Application application, Face rackFace, Edge rackEdge, int noTeeth, double rackHeight, double rackWidth, double rackExtents, PartFeatureExtentDirectionEnum rackFeatureExtentDirection) 
		{
			m_application = application;
			m_rackFace = rackFace;
			m_rackEdge = rackEdge;
			m_noTeeth = noTeeth;
			m_rackHeight = rackHeight;
			m_rackWidth = rackWidth;
			m_rackExtents = rackExtents;
			m_rackFeatureExtentDirection = rackFeatureExtentDirection;		
		}
		
		public override void OnExecute (Document document, NameValueMap context, bool succeeded)
		{
			//execute command functionality
			PartDocument partDocument = (PartDocument)document;

			PartComponentDefinition partCompDef = partDocument.ComponentDefinition;

			//get rack edge start point and end point
			Vertex rackEdgeStartVertex = m_rackEdge.StartVertex;

			Point rackEdgeStartPt = rackEdgeStartVertex.Point;

			Vertex rackEdgeStopVertex = m_rackEdge.StopVertex;
			
			Point rackEdgeStopPt = rackEdgeStopVertex.Point;

			double rackEdgeLength = rackEdgeStartPt.DistanceTo(rackEdgeStopPt);

			double nonRackWidth = rackEdgeLength - m_rackWidth;

			double toothWidthProportion = 0.25;

			double toothMajorWidth  = m_rackWidth  / (m_noTeeth + (m_noTeeth - 1) * toothWidthProportion);

			double toothMinorWidth = toothWidthProportion * toothMajorWidth;

			double toothSlopeWidth = (toothMajorWidth - toothMinorWidth) / 2.0;

			double rackStart = nonRackWidth / 2.0;

			TransientGeometry transientGeometry = m_application.TransientGeometry;

			TransientObjects transientObjects = m_application.TransientObjects;

			object objEnumerator = null;
			ObjectCollection sketchLineCollection = transientObjects.CreateObjectCollection(objEnumerator);

			WorkPlanes workPlanes = partCompDef.WorkPlanes;

			WorkPlane workPlane = workPlanes.AddByLinePlaneAndAngle(m_rackEdge, m_rackFace, "90 deg", false);

			workPlane.Visible = false;

			PlanarSketches planarSketches = partCompDef.Sketches;

			PlanarSketch planarSketch = planarSketches.AddWithOrientation(workPlane, m_rackEdge, true, true, rackEdgeStartVertex, false); 

			SketchPoints sketchPoints = planarSketch.SketchPoints;

			SketchLines sketchLines = planarSketch.SketchLines;

			Point2d point1, point2, point3, point4;
			SketchPoint sketchPoint1, sketchPoint2, sketchPoint3, sketchPoint4;
			SketchLine sketchLine1, sketchLine2, sketchLine3, sketchLine4;

			for (int toothCt = 0;toothCt < m_noTeeth; toothCt++)
			{
				point1 = transientGeometry.CreatePoint2d(rackStart, 0);
				point2 = transientGeometry.CreatePoint2d(rackStart + toothSlopeWidth, -m_rackHeight);
				point3 = transientGeometry.CreatePoint2d(rackStart + toothSlopeWidth + toothMinorWidth, -m_rackHeight);
				point4 = transientGeometry.CreatePoint2d(rackStart + toothMajorWidth, 0);

				sketchPoint1 = sketchPoints.Add(point1, false);
				sketchPoint2 = sketchPoints.Add(point2, false);
				sketchPoint3 = sketchPoints.Add(point3, false);
				sketchPoint4 = sketchPoints.Add(point4, false);

				sketchLine1 = sketchLines.AddByTwoPoints(sketchPoint1, sketchPoint2);
                sketchLine2 = sketchLines.AddByTwoPoints(sketchPoint2, sketchPoint3);
                sketchLine3 = sketchLines.AddByTwoPoints(sketchPoint3, sketchPoint4);
                sketchLine4 = sketchLines.AddByTwoPoints(sketchPoint4, sketchPoint1);
								
				sketchLineCollection.Add(sketchLine1);
				sketchLineCollection.Add(sketchLine2);
				sketchLineCollection.Add(sketchLine3);
				sketchLineCollection.Add(sketchLine4);

				sketchLine1 = null;
				sketchLine2 = null;
				sketchLine3 = null;
				sketchLine4 = null;

				point1 = null;
				point2 = null;
				point3 = null;
				point4 = null;

				sketchPoint1 = null;
				sketchPoint2 = null;
				sketchPoint3 = null;
				sketchPoint4 = null;

				rackStart += (toothMajorWidth + toothMinorWidth);
			}

			Profiles profiles = planarSketch.Profiles;

			Profile profile = profiles.AddForSolid(true, sketchLineCollection, 0);

			PartFeatures partFeatures = partCompDef.Features;

            ExtrudeFeatures extrudeFeatures = partFeatures.ExtrudeFeatures;

            ExtrudeFeature rackExtrudeFeature = extrudeFeatures.AddByDistanceExtent(profile, m_rackFeatureExtentDirection == PartFeatureExtentDirectionEnum.kSymmetricExtentDirection ? m_rackExtents *= 2 : m_rackExtents, m_rackFeatureExtentDirection, PartFeatureOperationEnum.kCutOperation, 0);
		}
	}
}
